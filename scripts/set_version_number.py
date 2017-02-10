#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import os
import re

def replace_in_file(path, regex, replacement):
    regex = re.compile(regex)

    lines = []
    with open(path) as infile:
        for line in infile:
            lines.append(re.sub(regex, replacement, line))

    with open(path, 'w') as outfile:
        for line in lines:
            outfile.write(line)

def update_cpp_file(path, version):
    version_parts = version.split('.')

    replace_in_file(path, 'LootVersion::major = \d+;', 'LootVersion::major = {};'.format(version_parts[0]))
    replace_in_file(path, 'LootVersion::minor = \d+;', 'LootVersion::minor = {};'.format(version_parts[1]))
    replace_in_file(path, 'LootVersion::patch = \d+;', 'LootVersion::patch = {};'.format(version_parts[2]))

def update_resource_file(path, version):
    comma_separated_version = version.replace('.', ', ')

    replace_in_file(path, 'VERSION \d+, \d+, \d+', 'VERSION {}'.format(comma_separated_version))
    replace_in_file(path, 'Version", "\d+\.\d+\.\d+"', 'VERSION ", "{}"'.format(version))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = 'Set the LOOT API version number')
    parser.add_argument('version', nargs='+')

    arguments = parser.parse_args()

    if len(arguments.version) != 1:
        raise RuntimeError('Invalid number of arguments given. Only one argument (the new version number) is expected.')

    if len(arguments.version[0].split('.')) != 3:
        raise RuntimeError('The version number must be a three-part semantic version.')

    update_cpp_file(os.path.join('src', 'api', 'loot_version.cpp.in'), arguments.version[0])
    update_resource_file(os.path.join('src', 'api', 'resource.rc'), arguments.version[0])

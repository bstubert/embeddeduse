#!/usr/bin/python3

import argparse
import subprocess
import sys

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('path', nargs='?', default='.', action='store',
        help='Path to Dockerfile (default: .)')
    args = parser.parse_args()

    result = subprocess.run(['docker', 'build',
        '--tag', 'docker-private-repos:0.1', args.path])
    print('Docker command: ', ' '.join(result.args))
    return result.returncode

if __name__ == '__main__':
    sys.exit(main())


#!/usr/bin/python3

import os
import subprocess
import sys

def main():
    command = ['/bin/bash'] if len(sys.argv) == 1 else sys.argv[1:]
    host_ssh_dir = os.path.join(os.environ['HOME'], ".ssh")
    ssh_auth_sock = os.environ['SSH_AUTH_SOCK']
    result = subprocess.run(['docker', 'run', '-it', '--rm',
        '-v', '{0}:/home/builder/.ssh:rw'.format(host_ssh_dir),
        '-v', '{0}:/ssh.socket'.format(ssh_auth_sock),
        '-e', 'SSH_AUTH_SOCK=/ssh.socket',
        '-e', 'USER_ID={0}'.format(os.getuid()),
        "-e", 'GROUP_ID={0}'.format(os.getgid()),
        'docker-private-repos:0.1'] + command)
    print('Docker command: ', ' '.join(result.args))
    return result.returncode

if __name__ == '__main__':
    sys.exit(main())

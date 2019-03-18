# configfix
Remove empty lines and comments from config files
# Usage
`configfix /etc/samba/smb.conf` - remove empty lines and comments from `/etc/samba/smb.conf`. Original file is saved to `/etc/samba/smb.conf.bak`.

`configfix` - read STDIN, remove comments and empty lines, and output to STDOUT.

`configfix -v` or `configfix --version` - displays program version

`configfix -h` or `configfix --help` - shows help, author and license informations
# License
Program is shared under GNU GPL V3 license, for more informations see https://www.gnu.org/licenses/gpl-3.0.en.html
# Compilation
Clone git repository, and run `make`, then `sudo make install` to install configfix to `/usr/local/bin/`
# Supported OS and architectures
Program should work on anything that has GCC 8. Tested with Archlinux (x86_64), FreeBSD 12.0 (x86_64), Ubuntu Server 16.04 (armv7l)

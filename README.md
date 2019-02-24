# configfix
Remove empty lines and comments from config files
# Usage
`configfix -f /etc/samba/smb.conf` - remove empty lines and comments from `/etc/samba/smb.conf`. Original file is saved to `/etc/samba/smb.conf.bak`.

`configfix` - read STDIN, remove comments and empty lines, and output to STDOUT.

`configfix -V` or `configfix --version` - displays program version

`configfix -h` or `configfix --help` - shows help, author and license informations

# Comments
Program interprets `#` and `;` as comments indicators. You can override this by using command line options:
`configfix -c '!*'` will cause `!` and `*` to be interpreted as comment indicator
# Statistics
use `-s` or `--stats` to display summary at end of program (STDERR)
# License
Program is shared under GNU GPL V3 license, for more informations see https://www.gnu.org/licenses/gpl-3.0.en.html

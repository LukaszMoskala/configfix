# configfix
Remove empty lines and comments from config files
# Usage
`configfix -f /etc/samba/smb.conf` - remove empty lines and comments from `/etc/samba/smb.conf`. Original file is saved to `/etc/samba/smb.conf.bak`.

`configfix` - read STDIN, remove comments and empty lines, and output to STDOUT.

`configfix -V` or `configfix --version` - displays program version, and compilation time

`configfix -O` or `configfix --oversion` - displays only version

`configfix -h` or `configfix --help` - shows help, author and license informations

You can use `configfix /path/to/file` without `-f` switch, but filename must be the only argument
# Comments
Program interprets `#` and `;` as comments indicators. You can override this by using command line options:
`configfix -c '!*'` will cause `!` and `*` to be interpreted as comment indicator
# Statistics
use `-s` or `--stats` to display summary at end of program (STDERR)

Example output:
```
Removed tailing whitespaces: 1
Removed comments: 4
        (characters: 179)
Removed empty lines: 5
```
# License
Program is shared under GNU GPL V3 license, for more informations see https://www.gnu.org/licenses/gpl-3.0.en.html
# Compilation on Linux-based systems
```
git clone https://github.com/LukaszMoskala/configfix.git
cd configfix
make
sudo make install
```
Program will be installed to `/usr/local/bin/`. Override this setting by using `sudo make PREFIX=/usr install` to install to `/usr/bin/` or any directory that you want

Note that on FreeBSD you have to use `gmake` instead of `make`
# Compilation on Windows
I don't see any reason to use this program on windows, because there is almost no config files. Program should compile anyway, but I have no way of testing this. If you were able to run it on windows, create pull request with changes to readme with instructions so others may use it too
# Supported OS and architectures
Program should work on anything that has GCC 8. Tested with Archlinux (x86_64), FreeBSD 12.0 (x86_64), Ubuntu Server 16.04 (armv7l)

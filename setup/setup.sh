#
# setup.sh
#
# setup script for mxcstool
#
# 2023.07.13 Mikio Morii
#

#
# This script must be loaded by "source" command of bash,
# before using mxcstool
#

#
# HEADAS
#

HEADAS_VER=6.30.1
export HEADAS=/soft/heasoft/${HEADAS_VER}/x86_64-pc-linux-gnu-libc2.17
source $HEADAS/headas-init.sh
export PGPLOT_TYPE=/xw

#
# change the terminal title
#

termtitle="mxcstool"
PROMPT_COMMAND='echo -ne "\033]0;${termtitle}\007"'

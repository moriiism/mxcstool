#
# setup.sh
#
# setup script for mxsim_helper
#
# 2023.07.28 Mikio Morii
#

#
# This script must be loaded by "source" command of bash,
# before using mxsim_helper
#

#
# HEADAS
#

HEADAS_VER=6.30.1
export HEADAS=/soft/heasoft/${HEADAS_VER}/x86_64-pc-linux-gnu-libc2.17
source $HEADAS/headas-init.sh
export PGPLOT_TYPE=/xw

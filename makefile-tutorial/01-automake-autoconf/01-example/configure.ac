# Must init the AutoConf setup
# The first parameter is project name
# The second parameter is version number
# The third parameter is bug report address
AC_INIT([hello], [1.0])

# Safety checks in case user overwritten -- srcdir
AC_CONFIG_SRCDIR([hello.c])

# Store the auxiliary build tools (e.g., install-sh, config.sub,  config.guess)
# in this dir (build-aux)

AC_CONFIG_AUX_DIR([build-aux])

# Init AutoMake, and specify this program use relaxed structures.
# i.e this program doesn't follow the gnu coding standards, and doesn't have
# ChangeLog, COPYING, AUTHORS, INSTALL, README etc. files.
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Check for c Compiler
AC_PROG_CC
# We can add more checks in this section

# Tells automake to create a Makefile
AC_CONFIG_FILES([Makefile])

# Generate the ouptut
AC_OUTPUT

dnl Function to detect if libvsmbr dependencies are available
AC_DEFUN([AX_LIBVSMBR_CHECK_LOCAL],
 [dnl Check for internationalization functions in libvsmbr/libvsmbr_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])


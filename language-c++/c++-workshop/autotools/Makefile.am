AUTOMAKE_OPTIONS = foreign

# Binary program
bin_PROGRAMS = hello
hello_SOURCES = main.cc

# Accept libhello directory and make library libhello.a
SUBDIRS = libhello
noinst_LIBRARIES = libhello/libhello.a
libhello_libhello_a_SOURCES = libhello/hello.cc
hello_LDADD = libhello/libhello.a

import os
from building import * 

# get current dir path
cwd = GetCurrentDir()

# init src and inc vars
src = []
inc = []

# add lib common include
inc += [cwd + '/libtest']

# add lib basic code
src += ['./libtest/libtest_hash.c'] 
src += ['./libtest/libtest_hexdump.c'] 
src += ['./libtest/libtest_usage.c'] 

# add group to IDE project
objs = DefineGroup('libtest-1.1.0', src, depend = ['PKG_USING_LIBTEST'], CPPPATH = inc) 

Return('objs') 

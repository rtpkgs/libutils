import os
from building import * 

# get current dir path
cwd = GetCurrentDir()

# init src and inc vars
src = []
inc = []

# add lib common include
inc += [cwd + '/libutils']

# add lib basic code
src += ['./libutils/hash.c'] 
src += ['./libutils/hexdump.c'] 
src += ['./libutils/usage.c'] 
src += ['./libutils/console.c'] 

# add group to IDE project
objs = DefineGroup('libutils-1.1.0', src, depend = ['PKG_USING_LIBUTILS'], CPPPATH = inc) 

Return('objs') 

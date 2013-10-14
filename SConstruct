import os

env = Environment(env=os.environ)
env['CFLAGS'] = ['-std=c11', '-O2', '-Iext/seatest/src', '-Iext/critbit', '-Isrc', '-Wall', '-Werror']

env.StaticLibrary('lib/libcritbit.a', ['ext/critbit/critbit.c'])
env.Program('tests/sanity.test', ['tests/sanity.test.c', 'ext/seatest/src/seatest.c', 'lib/libcritbit.a'])
env.Program('tests/suffer_api.test', ['tests/suffer_api.test.c', 'src/suffer_api.c', 'ext/seatest/src/seatest.c', 'lib/libcritbit.a'])

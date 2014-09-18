require 'mkmf'

$DEBUG = true
$libs += " -llapack -lcblas -latlas"

$INSTALLFILES = [['odepack.h', '$(archdir)'], ['oderb.so', '$(archdir)']]

path = File.expand_path("../odepack", __FILE__)
odepack_c = Dir::entries(path).select {|str| str =~ /(.+)\.f/}
odepack_obj = odepack_c.map{|str| str.gsub(".f", ".o")}
other_c = %w{oderb.c}
other_obj = other_c.map{|str| str.gsub(".c", ".o")}

$objs = odepack_obj + other_obj
$srcs = odepack_c + other_c

create_makefile("oderb")

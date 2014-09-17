require "bundler/gem_tasks"
require "rake/clean"
require "rbconfig"

CLOBBER.include('*.o', '*.so')

CFLAGS = RbConfig::CONFIG["CFLAGS"]
HDRDIR = RbConfig::CONFIG["rubyhdrdir"]
ARCHHDRDIR = RbConfig::CONFIG["rubyarchhdrdir"]

path = File.expand_path("../ext/oderb/odepack", __FILE__)
ODEPACK_C = Dir::entries(path).select {|str| str =~ /(.+)\.f/}
ODEPACK_OBJECTS = ODEPACK_C.map{|str| str.gsub(".f", ".o")}

task :main => "oderb.so"
task :default => :main

file "oderb.so" => ["oderb.o"] + ODEPACK_OBJECTS do |t|
  str = (["oderb.o"] + ODEPACK_OBJECTS).inject(""){|memo, file| memo + " " + file}
  sh "gcc -shared -o oderb.so" + str + " -lgfortran -lm"
end

ODEPACK_C.zip(ODEPACK_OBJECTS).each do |pair|
  c_path = File.expand_path("./" + pair[0], path)
  obj_name = pair[1]
  file obj_name  => c_path do |t|
    compile(t.prerequisites.first, t.name)
  end
end

file "oderb.o" => File.expand_path("../ext/oderb/oderb.c", __FILE__) do |t|
  compile_c_for_ruby(t.prerequisites.first, t.name)
end

def compile(src, target)
	sh "gcc -c -fPIC -o #{target} #{src}"
end

def compile_c_for_ruby(src, target)
	sh "gcc -c -I #{ARCHHDRDIR} -I#{HDRDIR} #{CFLAGS} -o #{target} #{src}"
end

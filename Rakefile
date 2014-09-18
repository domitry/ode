require 'bundler'
require 'rake/extensiontask'

Bundler::GemHelper.install_tasks
Bundler.setup(:default, :development)

Rake::ExtensionTask.new do |ext|
  ext.name = 'oderb'
  ext.ext_dir = 'ext/oderb'
  ext.lib_dir = 'lib/'
  ext.source_pattern = "**/*.{f, c, h}"
end

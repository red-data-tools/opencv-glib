#!/usr/bin/env ruby

require "pathname"

gem "test-unit"
require "test-unit"

base_dir = Pathname(__dir__).parent
test_dir = base_dir + "test"

require "gi"

CV = GI.load("CV")

require "tempfile"
require_relative "helper/fixture"

exit(Test::Unit::AutoRunner.run(true, test_dir.to_s))

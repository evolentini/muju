require 'ceedling/plugin'

class Freertos < Plugin

    # Set up Ceedling to use this plugin.
  def setup
    # Get the location of this plugin.
    @plugin_root = File.expand_path(File.join(File.dirname(__FILE__), '..'))
    puts "Support for FreeRTOS enabled..."

    # Add the path to fff.h to the include paths.
    COLLECTION_PATHS_TEST_SUPPORT_SOURCE_INCLUDE_VENDOR << "#{@plugin_root}/vendor/freertos/portable/GCC/POSIX"
    COLLECTION_PATHS_TEST_SUPPORT_SOURCE_INCLUDE_VENDOR << "#{@plugin_root}/vendor/freertos/include"
    COLLECTION_PATHS_TEST_SUPPORT_SOURCE_INCLUDE_VENDOR << "#{@plugin_root}/vendor/freertos"
    COLLECTION_PATHS_TEST_SUPPORT_SOURCE_INCLUDE_VENDOR << "#{@plugin_root}/src"

  end

  def pre_build
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/croutine.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/event_groups.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/list.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/queue.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/tasks.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/timers.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/portable/GCC/Posix/port.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/vendor/freertos/portable/MemMang/heap_3.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/src/support.c"
    COLLECTION_ALL_SOURCE << "#{@plugin_root}/src/main.c"
  end

  def post_runner_generate(arg_hash)
    # After the test runner file has been created, append the FFF globals
    # definition to the end of the test runner. These globals will be shared by
    # all mocks linked into the test.
    test = File.read(arg_hash[:test_file])
    if test.include?'#include "FreeRTOS.h"' 
      puts "Adding support for FreeRTOS to runner..."
      runner = File.read(arg_hash[:runner_file])
      runner = modify_headers(runner)
      runner = modify_main(runner)
      File.open(arg_hash[:runner_file], "w") do |output|
        output.write(runner)
      end
    end
  end

  def modify_headers(runner)
    headers = ['FreeRTOS.h', 'task.h']
    statements = ""
    headers.each do |header|
      statements += "#include \"#{header}\"\n"
    end
    return runner.gsub(/(#include <stdio.h>\n)/, "\\1#{statements}")
  end

  def modify_main(runner)
    regex = /(\s{2}RUN_TEST\([\w\s\,]*\);\n)+/
    stack = "configMINIMAL_STACK_SIZE"
    priority = "configMAX_PRIORITIES - 1"
    start_task = "  xTaskCreate(task_run_test, \"Tests\", #{stack}, NULL, #{priority}, NULL);\n"
    start_task += "  vTaskStartScheduler();\n"

    tests_run = runner.match(regex)
    runner = runner.gsub(regex, start_task)

    task_definition = "/*=======Tests Runner Task=======*/\n"
    task_definition += "void task_run_test(void * parameter)\n"
    task_definition += "{\n#{tests_run}  vTaskEndScheduler();\n}\n"

    regex = /(\n\/\*=*MAIN=*\*\/\n)/
    return runner.gsub(regex, "#{task_definition}\\1")
  end

end # class FakeFunctionFramework

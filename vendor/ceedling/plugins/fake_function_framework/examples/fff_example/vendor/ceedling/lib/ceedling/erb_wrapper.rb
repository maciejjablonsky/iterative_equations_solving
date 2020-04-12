require 'erb'

class ErbWrapper
  def generate_file(template, elements, output_file)
    File.open(output_file, "w") do |f|
      f << ERB.new(template, 0, "<>").result(binding)
    end
  end
end
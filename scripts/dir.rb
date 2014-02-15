#Directions towards Northeast Customs: GO Northeast Gate and you're there.
#>go northeast gate and you're there.
#Please rephrase that command.

def dir
  put "dir #{$args.join(" ")} 100"
  m = match_get({ :go => [/Directions towards|don't know the way/] })
  m[:match].gsub(/.*:/, '').split(/,/).collect(&:strip)
end

dir.each do |dir|
  if dir =~ /west|south|north|east|go|out/i
    move dir.downcase
  end
end

put "dir stop"
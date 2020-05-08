#!/usr/bin/ruby

totalOS = 111
totalANF = 222

Hum = Hash['projeto' => totalOS, 
  "b" => totalANF]
Hdois = Hash["projeto" => totalOS*2, "b" => totalANF*2]

H = Hum

puts "#{H['a']}"
puts "#{H['b']}"

puts ''

keys = H.keys
puts "#{keys}"

values = H.values
puts "#{values}"

puts ''

H.each do |key, value|
  puts "#{key}: #{value}"
end

puts ''
puts ''

variavelArray = [Hum]

variavelArray.each do |i|
   i.each do |key, value|
      puts "#{key}: #{value}"
   end
end

puts ''
puts ''

for j in variavelArray
   puts j['projeto']
end


puts ''
puts ''



variavelArray.push Hdois

variavelArray.each do |i|
   i.each do |key, value|
      puts "#{key}: #{value}"
   end
end
puts ''
puts ''



ary = [31,42,43,44,45]
ary.each_with_index do |i, index|
   puts i.to_s + ' - ' + index.to_s
end

puts '_____________'
puts '_____________'


ras = Hash['um' => 0, 'dois' => 0]
ras['um' => 1]
puts ras['um']

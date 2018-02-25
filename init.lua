srv = net.createServer(net.UDP)
srv:listen(5000)
srv:on("receive", function(s, data)
        uart.write(0, data);
end)

uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)
dofile('udp.lua');


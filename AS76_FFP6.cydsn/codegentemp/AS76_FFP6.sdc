# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Revanth\Documents\GitHub\AS76_FFP\AS76_FFP\AS76_FFP6.cydsn\AS76_FFP6.cyprj
# Date: Mon, 05 Aug 2024 13:05:54 GMT
#set_units -time ns
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {PWM_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock_Encoder_24Mhz} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {SPIM_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {UART_PCB_LOG_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 53 105} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_4}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\Revanth\Documents\GitHub\AS76_FFP\AS76_FFP\AS76_FFP6.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Revanth\Documents\GitHub\AS76_FFP\AS76_FFP\AS76_FFP6.cydsn\AS76_FFP6.cyprj
# Date: Mon, 05 Aug 2024 13:05:43 GMT

OLED_TRANSPORT = spi
OLED_ENABLE = yes
RAW_ENABLE = yes
CONSOLE_ENABLE = yes
Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto

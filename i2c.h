extern void i2c_start(void);
extern void i2c_write(unsigned char);
extern unsigned char i2c_read(void);
extern void i2c_ack(void);
extern void i2c_noack(void);
extern void i2c_stop();
extern void i2c_device_write(unsigned char,unsigned char,unsigned char);
extern unsigned char i2c_device_read(unsigned char,unsigned char);
extern void i2c_delay(void);

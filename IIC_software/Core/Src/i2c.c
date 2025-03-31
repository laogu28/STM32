#include "i2c.h"

//iic delay函数 
static void iic_delay(void)
{
    delay_us(2);
}

//iic起始信号 
void iic_start(void)
{
    //保持时钟线高电平，数据线产生下降沿
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);
    iic_delay();

    //拉低时钟线，准备发送/接收数据
    IIC_SCL(0);
    iic_delay();
}

//iic停止信号
void iic_stop(void)
{
    /* 保持时钟线高电平，数据线产生上升沿 
    IIC_SDA(0);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);
    iic_delay();
}

//等待应答信号 
//return 0:fail 1:succeed
uint8_t iic_wait_ack (void)
{
    IIC_SDA(1);    //主机释放SDA线
    iic_delay();
    IIC_SCL(1);    //拉高SCL等待读取从机应答信号
    iic_delay();
    if (IIC_READ_SDA) //SCL高电平读取SDA状态
    {
        iic_stop();     //SDA高电平表示从机非应答
        return 0;
    }
    IIC_SCL(0);         // SCL低电平表示结束应答检查
    iic_delay();
    return 1;
}

//应答信号 
void iic_ack(void)
{
    IIC_SCL(0);
    iic_delay();
    IIC_SDA (0);  //数据线为低电平，表示应答 
    iic_delay();
    IIC_SCL(1);
    iic_delay();
}

//非应答信号 
void iic_nack(void)
{
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);  //数据线为高电平，表示非应答 
    iic_delay();
    IIC_SCL(1);
    iic_delay();
}

//发送一个字节数据 
void iic_send_byte(uint8_t data)
{
    for (uint8_t t=0; t<8; t++)
    {
        //高位先发 
        IIC_SDA((data & 0x80) >> 7);
        iic_delay();
        //拉高时钟线，稳定数据接收 
        IIC_SCL (1);
        iic_delay();
        
        IIC_SCL (0);
        data <<= 1;     //左移1位, 用于下一次发送 
    }
    IIC_SDA (1);      //发送完成,主机释放SDA线 
}

//读取1字节数据 
/* ack:通知从机是否继续发送。
   0,停止发送;1,继续发送*/
uint8_t iic_read_byte(uint8_t ack)
{ 
    uint8_t receive = 0 ;
    for (uint8_t t=0; t<8; t++)
    {
        //高位先输出，先收到的数据位要左移
        receive <<= 1;
        IIC_SCL(1);
        iic_delay();
        if (IIC_READ_SDA) 
        {
            receive++;
        }
        IIC_SCL(0);
        iic_delay();
    }
    //判断是否继续读取从机数据
    if ( !ack ) 
    {
        iic_nack();
    }
    else 
    {
        iic_ack();
    }
    return receive;
}


//at24c02部分

//写入一个字节到从机AT24C02中
void at24c02_write_one_byte(uint8_t addr, uint8_t data)
{
    //1、发送起始信号 
    iic_start();
    
    //2、发送通讯地址(写操作地址) 
    iic_send_byte(0xA0);
    
    //3、等待应答信号 
    iic_wait_ack();
    
    // 4、发送内存地址:0~255 
    iic_send_byte(addr);
    
    // 5、等待应答信号 
    iic_wait_ack();
    
    // 6、发送写入数据 
    iic_send_byte(data);
    
    //7、等待应答信号 
    iic_wait_ack();
    
    // 8、发送停止信号 
    iic_stop();
    
    //等待EEPROM写入完成
    delay_ms(10);
}

//往从机AT24C02中读取一个字节
uint8_t at24c02_read_one_byte(uint8_t addr)
{
    uint8_t read = 0;
    
    // 1、发送起始信号
    iic_start();
    
    // 2、发送通讯地址(写操作地址) 
    iic_send_byte(0xA0);
    
    // 3、等待应答信号
    iic_wait_ack();
    
		// 4、发送内存地址:0~255 
    iic_send_byte(addr);
    
    // 5、等待应答信号
    iic_wait_ack();
    
    //6、发送起始信号 
    iic_start();
    
    // 7、发送通讯地址(读操作地址)
    iic_send_byte(0xA1);
    
    // 8、等待应答信号 
    iic_wait_ack();
    
    // 9、接收数据并发送非应答(获取该地址即可) 
    read = iic_read_byte(0);
    
    // 10、发送停止信号
    iic_stop();
    
    return read;
}



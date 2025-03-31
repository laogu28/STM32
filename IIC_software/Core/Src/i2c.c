#include "i2c.h"

//iic delay���� 
static void iic_delay(void)
{
    delay_us(2);
}

//iic��ʼ�ź� 
void iic_start(void)
{
    //����ʱ���߸ߵ�ƽ�������߲����½���
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);
    iic_delay();

    //����ʱ���ߣ�׼������/��������
    IIC_SCL(0);
    iic_delay();
}

//iicֹͣ�ź�
void iic_stop(void)
{
    /* ����ʱ���߸ߵ�ƽ�������߲��������� 
    IIC_SDA(0);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);
    iic_delay();
}

//�ȴ�Ӧ���ź� 
//return 0:fail 1:succeed
uint8_t iic_wait_ack (void)
{
    IIC_SDA(1);    //�����ͷ�SDA��
    iic_delay();
    IIC_SCL(1);    //����SCL�ȴ���ȡ�ӻ�Ӧ���ź�
    iic_delay();
    if (IIC_READ_SDA) //SCL�ߵ�ƽ��ȡSDA״̬
    {
        iic_stop();     //SDA�ߵ�ƽ��ʾ�ӻ���Ӧ��
        return 0;
    }
    IIC_SCL(0);         // SCL�͵�ƽ��ʾ����Ӧ����
    iic_delay();
    return 1;
}

//Ӧ���ź� 
void iic_ack(void)
{
    IIC_SCL(0);
    iic_delay();
    IIC_SDA (0);  //������Ϊ�͵�ƽ����ʾӦ�� 
    iic_delay();
    IIC_SCL(1);
    iic_delay();
}

//��Ӧ���ź� 
void iic_nack(void)
{
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);  //������Ϊ�ߵ�ƽ����ʾ��Ӧ�� 
    iic_delay();
    IIC_SCL(1);
    iic_delay();
}

//����һ���ֽ����� 
void iic_send_byte(uint8_t data)
{
    for (uint8_t t=0; t<8; t++)
    {
        //��λ�ȷ� 
        IIC_SDA((data & 0x80) >> 7);
        iic_delay();
        //����ʱ���ߣ��ȶ����ݽ��� 
        IIC_SCL (1);
        iic_delay();
        
        IIC_SCL (0);
        data <<= 1;     //����1λ, ������һ�η��� 
    }
    IIC_SDA (1);      //�������,�����ͷ�SDA�� 
}

//��ȡ1�ֽ����� 
/* ack:֪ͨ�ӻ��Ƿ�������͡�
   0,ֹͣ����;1,��������*/
uint8_t iic_read_byte(uint8_t ack)
{ 
    uint8_t receive = 0 ;
    for (uint8_t t=0; t<8; t++)
    {
        //��λ����������յ�������λҪ����
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
    //�ж��Ƿ������ȡ�ӻ�����
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


//at24c02����

//д��һ���ֽڵ��ӻ�AT24C02��
void at24c02_write_one_byte(uint8_t addr, uint8_t data)
{
    //1��������ʼ�ź� 
    iic_start();
    
    //2������ͨѶ��ַ(д������ַ) 
    iic_send_byte(0xA0);
    
    //3���ȴ�Ӧ���ź� 
    iic_wait_ack();
    
    // 4�������ڴ��ַ:0~255 
    iic_send_byte(addr);
    
    // 5���ȴ�Ӧ���ź� 
    iic_wait_ack();
    
    // 6������д������ 
    iic_send_byte(data);
    
    //7���ȴ�Ӧ���ź� 
    iic_wait_ack();
    
    // 8������ֹͣ�ź� 
    iic_stop();
    
    //�ȴ�EEPROMд�����
    delay_ms(10);
}

//���ӻ�AT24C02�ж�ȡһ���ֽ�
uint8_t at24c02_read_one_byte(uint8_t addr)
{
    uint8_t read = 0;
    
    // 1��������ʼ�ź�
    iic_start();
    
    // 2������ͨѶ��ַ(д������ַ) 
    iic_send_byte(0xA0);
    
    // 3���ȴ�Ӧ���ź�
    iic_wait_ack();
    
		// 4�������ڴ��ַ:0~255 
    iic_send_byte(addr);
    
    // 5���ȴ�Ӧ���ź�
    iic_wait_ack();
    
    //6��������ʼ�ź� 
    iic_start();
    
    // 7������ͨѶ��ַ(��������ַ)
    iic_send_byte(0xA1);
    
    // 8���ȴ�Ӧ���ź� 
    iic_wait_ack();
    
    // 9���������ݲ����ͷ�Ӧ��(��ȡ�õ�ַ����) 
    read = iic_read_byte(0);
    
    // 10������ֹͣ�ź�
    iic_stop();
    
    return read;
}



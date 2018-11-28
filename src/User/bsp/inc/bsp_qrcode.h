/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_qrcode.h
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月9日 23:28:13
  最近修改   :
  功能描述   : bsp_qrcode.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年9月9日 23:28:13
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BSP_QRCODE_H__
#define __BSP_QRCODE_H__

#ifdef __cplusplus
 extern "C" {
#endif 


// QR Code Format Encoding
#define MODE_NUMERIC        0
#define MODE_ALPHANUMERIC   1
#define MODE_BYTE           2


// Error Correction Code Levels
#define ECC_LOW            0
#define ECC_MEDIUM         1
#define ECC_QUARTILE       2
#define ECC_HIGH           3
	

// If set to non-zero, this library can ONLY produce QR codes at that version
// This saves a lot of dynamic memory, as the codeword tables are skipped
#ifndef LOCK_VERSION
#define LOCK_VERSION       0
#endif
	
typedef struct QRCode {
	uint8_t version;
	uint8_t size;
	uint8_t ecc;
	uint8_t mode;
	uint8_t mask;
	uint8_t *modules;
} QRCode;
	
uint16_t qrcode_getBufferSize(uint8_t version);

int8_t qrcode_initText(QRCode *qrcode, uint8_t *modules, uint8_t version, uint8_t ecc, const char *data);
int8_t qrcode_initBytes(QRCode *qrcode, uint8_t *modules, uint8_t version, uint8_t ecc, uint8_t *data, uint16_t length);

bool qrcode_getModule(QRCode *qrcode, uint8_t x, uint8_t y);


#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* __BSP_QRCODE_H__ */

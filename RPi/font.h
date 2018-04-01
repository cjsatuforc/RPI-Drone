#pragma once

unsigned char* RPI_GetFontCharacter(unsigned char);

enum rpi_text_encoding_t
{
	ASCII = 0,
	UTF8 = 1
};

void RPI_SetTextEncoding(rpi_text_encoding_t);
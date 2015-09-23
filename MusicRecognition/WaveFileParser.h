#ifndef	WAVEFILEPARSER_H_
#define	WAVEFILEPARSER_H_
#include <string.h>
#include <string>

//wave header
typedef struct tagwave_header_t
{
	unsigned char riff[4];					//��Դ�����ļ���־
	unsigned int size;							//���¸���ַ��ʼ���ļ���β���ֽ���
	unsigned char wave_flag[4];		//wave�ļ���ʶ
	unsigned char fmt[4];					//���θ�ʽ��ʶ
	unsigned int fmt_len;					//�����ֽڣ�һ��Ϊ0000 0010H��
	unsigned short tag;						//��ʽ���ֵ࣬Ϊ1ʱ����ʶPCM���Ա���
	unsigned short channels;			//ͨ������������Ϊ1��˫����Ϊ2
	unsigned int samp_freq;				//����Ƶ��
	unsigned int byte_rate;				//���ݴ����ʣ�ÿ���ֽ�=����Ƶ��*ÿ�������ֽ�����
	unsigned short block_align;		//������ֽ���=channels*bit_samp/8
	unsigned short bit_samp;			//bits per sample���ֳ�����λ����

	tagwave_header_t()
	{
		memset(this, 0, sizeof(tagwave_header_t));
	}
} wave_header_t;

typedef struct tagwave_file_t
{
	wave_header_t header;			//header
	char data_flag[4];						//���ݱ�ʶ��
	unsigned int length;				//������������
	unsigned char* pData;			//data

	tagwave_file_t()
	{
		memset(this, 0, sizeof(tagwave_file_t));
	}
	~tagwave_file_t()
	{
		if (pData)
		{
			delete[] pData;
			pData = NULL;
		}
	}
} wave_file_t;

class WaveFileParser
{
public:
	WaveFileParser() {}
	~WaveFileParser() {}

	const wave_file_t* Parse(const std::string& strFileName);
	int Construct(const std::string& strFileName, const char* pPCMBuffer, int nBufferSize, size_t bit_per_samp, size_t samp_freq);

private:
	wave_file_t m_stWaveFile;
};

#endif		//WAVEFILEPARSER_H_
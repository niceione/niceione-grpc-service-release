/**********************************************************************
*	FxImgProc.h
**********************************************************************/
#ifndef _IMG_PROC_HEADER
#define _IMG_PROC_HEADER

/////////////////////////////////////////////////////////////////
// Windows - Windows/Intel specific
#if defined(_WIN32) || defined(WIN32) || defined(_WINDOWS)

#ifndef WINAPI
#define WINAPI __stdcall
#endif

//#define FX_API_EXPORTS
#ifdef FX_API_EXPORTS
#define FX_API __declspec(dllexport)
#else
#define FX_API __declspec(dllimport)
#endif

#endif	//defined(_WIN32)

#ifdef __cplusplus
extern "C"
{
#endif

//인식된 신분증 데이터가 넘어올 구조체
typedef struct _IDCard_Info
{
	int  CardType;			//신분증 종류(0:판별불가, 1:주민등록증, 2:운전면허증 신형, 3:복지카드)
	char IDName[20];		//이름
	char IDNumber[20];		//주민번호
	char IssueDate[20];		//발급일자
	char Juso[128];			//주소
} IDCARD_INFO;

// 신분증 인식
FX_API int WINAPI FX_RecogID (char *upName, char *dnName, char *picName, char *fingerName, IDCARD_INFO *pCard, int kind);
/*
  char *upName, *dnName에 대하여 신분증 인식을 한다.(B&W, 16, 256Gray, Color 지원)
						(앞면만 넘길 경우 dnName에 NULL을 준다.)
  char *picName, *fingerName: 사진 및 지문 이미지파일 Path (NULL인 경우 생성 안함)
  IDCARD_INFO *pCard: 신분증의 인식된 데이터가 넘어올 구조체.
  kind: 0
  리턴값-> 1: OK
          -1: File Format 에러
	  -2: 지원되지 않는 이미지 bpp
*/

FX_API int WINAPI FX_RecogID_Ex (char *upName, char *dnName, char *picName, char *fingerName, IDCARD_INFO *pCard, RECT *r);
/*
  FX_RecogID(...) 참조
  RECT *r : 신분증 주민번호의 영역이 넘어온다.
*/

// 영역에 대한 블랙마스킹 처리
FX_API int WINAPI FX_MaskingProcess(char *szFilename, RECT *r);
/*
   신분증의 주민번호 영역에 대한 마스킹 처리 - 리턴 ==> 1: 정상, 0: 에러
   char *upName : 신분증 앞면이미지 경로
   RECT *r : 주민번호 영역
*/

#ifdef __cplusplus
}
#endif

#endif	// _IMG_PROC_HEADER

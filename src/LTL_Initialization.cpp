//��ʼ���ڲ�����

#include <corecrt_internal.h>


#ifndef __Bulib_Dynamic_Lib

static void __cdecl __LTL_Unitialization() throw()
{
	//__acrt_uninitialize_locks(false);


	__acrt_uninitialize_winapi_thunks(false);

}
#endif

EXTERN_C int __cdecl __LTL_Initialization() throw()
{
	//�ȳ�ʼ���߼�ָ��֧��
	__isa_available_init();

#ifndef __Bulib_Dynamic_Lib
	//��ʼ��winapi_thunks
	__acrt_initialize_winapi_thunks();
	
	//__acrt_initialize_locks();


	atexit(__LTL_Unitialization);
#endif
	return 0;
}


_CRTALLOC(".CRT$XIC") static _PIFV ___Initialization =  __LTL_Initialization;
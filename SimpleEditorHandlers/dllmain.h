// dllmain.h: объ€вление класса модул€.

class CSimpleEditorHandlersModule : public ATL::CAtlDllModuleT< CSimpleEditorHandlersModule >
{
public :
	DECLARE_LIBID(LIBID_SimpleEditorHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SIMPLEEDITORHANDLERS, "{968B9916-3B8A-43AC-AAC0-1B22F7CC3691}")
};

extern class CSimpleEditorHandlersModule _AtlModule;

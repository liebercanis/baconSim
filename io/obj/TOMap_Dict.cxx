// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TOMap_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TOMap.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TOMap(void *p = 0);
   static void *newArray_TOMap(Long_t size, void *p);
   static void delete_TOMap(void *p);
   static void deleteArray_TOMap(void *p);
   static void destruct_TOMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TOMap*)
   {
      ::TOMap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TOMap >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TOMap", ::TOMap::Class_Version(), "TOMap.hxx", 18,
                  typeid(::TOMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TOMap::Dictionary, isa_proxy, 4,
                  sizeof(::TOMap) );
      instance.SetNew(&new_TOMap);
      instance.SetNewArray(&newArray_TOMap);
      instance.SetDelete(&delete_TOMap);
      instance.SetDeleteArray(&deleteArray_TOMap);
      instance.SetDestructor(&destruct_TOMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TOMap*)
   {
      return GenerateInitInstanceLocal((::TOMap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TOMap*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TOMap::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TOMap::Class_Name()
{
   return "TOMap";
}

//______________________________________________________________________________
const char *TOMap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOMap*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TOMap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOMap*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TOMap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOMap*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TOMap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOMap*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TOMap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TOMap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TOMap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TOMap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TOMap(void *p) {
      return  p ? new(p) ::TOMap : new ::TOMap;
   }
   static void *newArray_TOMap(Long_t nElements, void *p) {
      return p ? new(p) ::TOMap[nElements] : new ::TOMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TOMap(void *p) {
      delete ((::TOMap*)p);
   }
   static void deleteArray_TOMap(void *p) {
      delete [] ((::TOMap*)p);
   }
   static void destruct_TOMap(void *p) {
      typedef ::TOMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TOMap

namespace ROOT {
   static TClass *maplEstringcOTOMapDetgR_Dictionary();
   static void maplEstringcOTOMapDetgR_TClassManip(TClass*);
   static void *new_maplEstringcOTOMapDetgR(void *p = 0);
   static void *newArray_maplEstringcOTOMapDetgR(Long_t size, void *p);
   static void delete_maplEstringcOTOMapDetgR(void *p);
   static void deleteArray_maplEstringcOTOMapDetgR(void *p);
   static void destruct_maplEstringcOTOMapDetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TOMapDet>*)
   {
      map<string,TOMapDet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TOMapDet>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TOMapDet>", -2, "map", 96,
                  typeid(map<string,TOMapDet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTOMapDetgR_Dictionary, isa_proxy, 4,
                  sizeof(map<string,TOMapDet>) );
      instance.SetNew(&new_maplEstringcOTOMapDetgR);
      instance.SetNewArray(&newArray_maplEstringcOTOMapDetgR);
      instance.SetDelete(&delete_maplEstringcOTOMapDetgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTOMapDetgR);
      instance.SetDestructor(&destruct_maplEstringcOTOMapDetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TOMapDet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,TOMapDet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTOMapDetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,TOMapDet>*)0x0)->GetClass();
      maplEstringcOTOMapDetgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTOMapDetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTOMapDetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TOMapDet> : new map<string,TOMapDet>;
   }
   static void *newArray_maplEstringcOTOMapDetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TOMapDet>[nElements] : new map<string,TOMapDet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTOMapDetgR(void *p) {
      delete ((map<string,TOMapDet>*)p);
   }
   static void deleteArray_maplEstringcOTOMapDetgR(void *p) {
      delete [] ((map<string,TOMapDet>*)p);
   }
   static void destruct_maplEstringcOTOMapDetgR(void *p) {
      typedef map<string,TOMapDet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,TOMapDet>

namespace {
  void TriggerDictionaryInitialization_TOMap_Dict_Impl() {
    static const char* headers[] = {
"TOMap.hxx",
0
    };
    static const char* includePaths[] = {
"/usr/local/root/include",
"/.",
"/home/admin/root-6.14.06/include",
"/home/gold/bacon/baconSim/io/obj/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TOMap_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace std{template <class _CharT> struct __attribute__((annotate("$clingAutoload$bits/char_traits.h")))  __attribute__((annotate("$clingAutoload$string")))  char_traits;
}
namespace std{template <typename > class __attribute__((annotate("$clingAutoload$bits/memoryfwd.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TOMap.hxx")))  TOMap;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TOMap_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TOMap.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TOMap", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TOMap_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TOMap_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TOMap_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TOMap_Dict() {
  TriggerDictionaryInitialization_TOMap_Dict_Impl();
}

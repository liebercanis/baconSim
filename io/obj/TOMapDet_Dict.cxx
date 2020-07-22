// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TOMapDet_Dict

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
#include "TOMapDet.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TOMapDet(void *p = 0);
   static void *newArray_TOMapDet(Long_t size, void *p);
   static void delete_TOMapDet(void *p);
   static void deleteArray_TOMapDet(void *p);
   static void destruct_TOMapDet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TOMapDet*)
   {
      ::TOMapDet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TOMapDet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TOMapDet", ::TOMapDet::Class_Version(), "TOMapDet.hxx", 15,
                  typeid(::TOMapDet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TOMapDet::Dictionary, isa_proxy, 4,
                  sizeof(::TOMapDet) );
      instance.SetNew(&new_TOMapDet);
      instance.SetNewArray(&newArray_TOMapDet);
      instance.SetDelete(&delete_TOMapDet);
      instance.SetDeleteArray(&deleteArray_TOMapDet);
      instance.SetDestructor(&destruct_TOMapDet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TOMapDet*)
   {
      return GenerateInitInstanceLocal((::TOMapDet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TOMapDet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TOMapDet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TOMapDet::Class_Name()
{
   return "TOMapDet";
}

//______________________________________________________________________________
const char *TOMapDet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOMapDet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TOMapDet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOMapDet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TOMapDet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOMapDet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TOMapDet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOMapDet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TOMapDet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TOMapDet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TOMapDet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TOMapDet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TOMapDet(void *p) {
      return  p ? new(p) ::TOMapDet : new ::TOMapDet;
   }
   static void *newArray_TOMapDet(Long_t nElements, void *p) {
      return p ? new(p) ::TOMapDet[nElements] : new ::TOMapDet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TOMapDet(void *p) {
      delete ((::TOMapDet*)p);
   }
   static void deleteArray_TOMapDet(void *p) {
      delete [] ((::TOMapDet*)p);
   }
   static void destruct_TOMapDet(void *p) {
      typedef ::TOMapDet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TOMapDet

namespace {
  void TriggerDictionaryInitialization_TOMapDet_Dict_Impl() {
    static const char* headers[] = {
"TOMapDet.hxx",
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
#line 1 "TOMapDet_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TOMapDet.hxx")))  TOMapDet;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TOMapDet_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TOMapDet.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TOMapDet", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TOMapDet_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TOMapDet_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TOMapDet_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TOMapDet_Dict() {
  TriggerDictionaryInitialization_TOMapDet_Dict_Impl();
}

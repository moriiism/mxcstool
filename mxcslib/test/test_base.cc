#include "mxcs_base.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

class TestObject: public MxcsObject{
public:
    explicit TestObject(string title = "") :
        MxcsObject("TestObject", title),
        member_("") {}
    ~TestObject() {
        Null();
    }
    void Set(string member) {member_ = member;};
    void Copy(const TestObject* const org);
    TestObject* const Clone() const;
    
    string GetMember() const {return member_;};

    void TestPrintErrWarnInfo() const;

private:
    string member_;
    void Null();
};

void TestObject::Copy(const TestObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    CopyTitle(org);
    Null();
    Set(org->GetMember());
}

TestObject* const TestObject::Clone() const
{
    TestObject* obj_new = new TestObject;
    obj_new->Copy(this);
    return obj_new;
}

void TestObject::TestPrintErrWarnInfo() const
{
    MxcsPrintErrClass("aaa");
    MxcsPrintWarnClass("bbb");
    MxcsPrintInfoClass("ccc");
}

void TestObject::Null()
{
    member_ = "";
}


int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
   
    // MxcsPrintErr(msg)
    // MxcsPrintWarn(msg)
    // MxcsPrintInfo(msg)
    // MxcsPrintErrVFunc
    {
        printf("--- test MxcsPrintErr, MxcsPrintWarn, "
               "MxcsPrintInfo, MxcsPrintErrVFunc\n");
        MxcsPrintErr("aaa");
        MxcsPrintWarn("bbb");
        MxcsPrintInfo("ccc");
        MxcsPrintErrVFunc;
        printf("=== \n");
    }

    // MxcsPrintErrClass(msg)
    // MxcsPrintWarnClass(msg)
    // MxcsPrintInfoClass(msg)
    {
        printf("--- test MxcsPrintErrClass, MxcsPrintWarnClass, "
               "MxcsPrintInfoClass\n");
        TestObject* test_obj = new TestObject("title");
        test_obj->TestPrintErrWarnInfo();
        printf("=== \n");
    }
    
    //    void IsValidArray(long narr, const long* const val_arr);
    {
        printf("--- test IsValidArray(long narr, const long* const val_arr)\n");
        long narr = 10;
        int* val_arr = new int[narr];
        MxcsBase::IsValidArray(narr, val_arr);
        delete [] val_arr;
        printf("=== \n");
    }

//    {
//        printf("--- test IsValidArray(long narr, const long* const val_arr)\n");
//        long narr = 10;
//        long* val_arr = new long[narr];
//        // AAA
//        MxcsBase::IsValidArray(0, val_arr, "invoke at AAA of test_base.cc");
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    {
//        printf("--- test IsValidArray(long narr, const long* const val_arr)\n");
//        long narr = 10;
//        long* val_arr = NULL;
//        // BBB
//        MxcsBase::IsValidArray(narr, val_arr,
//                               "invoke at BBB of test_base.cc");
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    void IsValidArray(long narr, const double* const val_arr);
    {
        printf("--- test IsValidArray(long narr, const double* const val_arr)\n");
        long narr = 10;
        double* val_arr = new double[narr];
        MxcsBase::IsValidArray(narr, val_arr);
        delete [] val_arr;
        printf("=== \n");
    }

//    {
//        printf("--- test IsValidArray(long narr,
//               const double* const val_arr)\n");
//        long narr = 10;
//        double* val_arr = new double[narr];
//        MxcsBase::IsValidArray(0, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    {
//        printf("--- test IsValidArray(long narr,
//                const double* const val_arr)\n");
//        long narr = 10;
//        double* val_arr = NULL;
//        MxcsBase::IsValidArray(narr, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    void GenArray(vector<double> vec,
//                  long* narr_ptr,
//                  double** val_arr_ptr);
//    void DelArray(double* val_arr);
    {
        printf("--- test GenArray, DelArray\n");
        vector<double> vec(3);
        vec[0] = 1.0;
        vec[1] = 2.0;
        vec[2] = 3.0;
        long narr = 0;
        double* val_arr = NULL;
        MxcsBase::GenArray(vec, &narr, &val_arr);
        for(long iarr = 0; iarr < narr; iarr ++){
            printf("%e\n", val_arr[iarr]);
        }
        MxcsBase::DelArray(val_arr);

        printf("=== \n");
    }
    
    return status_prog;
}

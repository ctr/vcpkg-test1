#include <cxxopts.hpp>
#include <fmt/format.h>
#include <range/v3/view.hpp>

// CTR - add matio demo
//#include <matio.h>

// CTR - try adding HighFive HDF5 library
#include <highfive/H5File.hpp>

namespace view = ranges::views;

int fib(int x)
{
  int a = 0, b = 1;

  for (int it : view::repeat(0) | view::take(x))
  {
    (void)it;
    int tmp = a;
    a += b;
    b = tmp;
  }

  return a;
}

int main(int argc, char **argv)
{
  cxxopts::Options options("fibo", "Print the fibonacci sequence up to a value 'n'");
  options.add_options()("n,value", "The value to print to", cxxopts::value<int>()->default_value("10"));

  auto result = options.parse(argc, argv);
  auto n = result["value"].as<int>();

  for (int x : view::iota(1) | view::take(n))
  {
    fmt::print("fib({}) = {}\n", x, fib(x));
  }

  // CTR - add matio demo from https://github.com/NJannasch/matio-examples/blob/master/Examples/saveVariable.cpp
  /* DOESN'T WORK -- no proper cmake integraton so won't link
  mat_t* matfp;
  const char* FILENAME = "myfile.mat";

  //Open file
  matfp = Mat_CreateVer(FILENAME, NULL, MAT_FT_MAT5);

  //string
  const char* fieldname1 = "MyStringVariable";
  const char* mystring = "Text";
  size_t dim1[2] = { 1, sizeof(mystring) / sizeof(mystring[0]) };
  matvar_t* variable1 = Mat_VarCreate(fieldname1, MAT_C_CHAR, MAT_T_UTF8, 2, dim1, (void*)mystring, 0);
  Mat_VarWrite(matfp, variable1, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
  Mat_VarFree(variable1);

  //integer
  const char* fieldname2 = "MyIntegerVariable";
  int myinteger = 42;
  size_t dim2[2] = { 1, 1 };
  matvar_t* variable2 = Mat_VarCreate(fieldname2, MAT_C_INT32, MAT_T_INT32, 2, dim2, &myinteger, 0);
  Mat_VarWrite(matfp, variable2, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
  Mat_VarFree(variable2);

  //double
  const char* fieldname3 = "MyDoubleVariable";
  double mydouble = 4.2;
  size_t dim3[2] = { 1, 1 };
  matvar_t* variable3 = Mat_VarCreate(fieldname3, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim3, &mydouble, 0);
  Mat_VarWrite(matfp, variable3, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
  Mat_VarFree(variable3);

  //complex double
  const char* fieldname4 = "MyComplexDoubleVariable";
  double real = 4.2;
  double imag = 1.5;
  mat_complex_split_t mycomplexdouble = { &real, &imag };
  size_t dim4[2] = { 1, 1 };
  matvar_t* variable4 = Mat_VarCreate(fieldname4, MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dim4, &mycomplexdouble, MAT_F_COMPLEX);
  Mat_VarWrite(matfp, variable4, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
  Mat_VarFree(variable4);

  //bool
  const char* fieldname5 = "MyBoolVariable";
  bool mybool = true;
  size_t dim5[2] = { 1, 1 };
  matvar_t* variable5 = Mat_VarCreate(fieldname5, MAT_C_INT16, MAT_T_INT16, 2, dim5, &mybool, MAT_F_LOGICAL);
  Mat_VarWrite(matfp, variable5, MAT_COMPRESSION_NONE); //or MAT_COMPRESSION_ZLIB
  Mat_VarFree(variable5);

  //Close file
  Mat_Close(matfp);
  return 0;
    */

  using namespace HighFive;

  std::string filename = "C:\\Temp\\new_file.h5";

  {
      // We create an empty HDF55 file, by truncating an existing
      // file if required:
      File file(filename, File::Truncate);

      std::vector<int> data(50, 1);
      file.createDataSet("grp/data", data);
  }

  {
      // We open the file as read-only:
      File file(filename, File::ReadOnly);
      auto dataset = file.getDataSet("grp/data");

      // Read back, with allocating:
      auto data = dataset.read<std::vector<int>>();

      // Because `data` has the correct size, this will
      // not cause `data` to be reallocated:
      dataset.read(data);
  }
}


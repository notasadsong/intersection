#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/class.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		///////////////////////////测试直线与直线求交点////////////////////////////
		
		TEST_METHOD(TestMethod1) //普通直线,正数双点
		{
			Line l1(0, 0, 1, 1);
			Line l2(0, 0, 0, 1);

			Point p = l1.getLLintersection(l2);
			Assert::AreEqual(true, p.x == 0 && p.y == 0);
		}

		TEST_METHOD(TestMethod2) //普通直线，含负数点
		{
			Line l1(1, 1, 2.5, 0);
			Line l2(-1, 5, 1, 1);

			Point p = l1.getLLintersection(l2);
			Assert::AreEqual(true, p.x == 1 && p.y == 1);
		}

		TEST_METHOD(TestMethod3) //平行直线，非xy轴平行
		{
			Line l1(2, 2, 4, 8);
			Line l2(4, 2, 6, 8);

			Assert::AreEqual(true, l1.parallel(l2));
		}

		TEST_METHOD(TestMethod4) //平行直线， 存在与x，y轴平行
		{
			Line l1(2, 2, 4, 2);
			Line l2(2, 4, 4, 4);

			Assert::AreEqual(true, l1.parallel(l2));
		}

		///////////////////////////////测试直线与圆求交点////////////////////////////////////

		TEST_METHOD(TestMethod5) //相离
		{
			Line l(2, 2, 4, 2);
			Circle c(1, 0, 1);

			vector<Point> v = c.get_c_l(l);
			bool flag = false;

			if (v.size() == 0) flag = true;
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod6) //相切
		{
			Line l(2, 2, 4, 2);
			Circle c(2, 0, 2);

			vector<Point> v = c.get_c_l(l);
			bool flag = false;

			if (v.size() == 1 && v[0].x == 2 && v[0].y == 2) flag = true;
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod7) //相交
		{
			Line l(2, 2, 4, 2);
			Circle c(2, 2, 1);

			vector<Point> v = c.get_c_l(l);
			bool flag = false;

			if (v.size() == 2) {
				if (v[0].x == 1 && v[0].y == 2 && v[1].x == 3 && v[1].y == 2) {
					flag = true;
				}
				if (v[0].x == 3 && v[0].y == 2 && v[1].x == 1 && v[1].y == 2) {
					flag = true;
				}
			}
			Assert::AreEqual(true, flag);
		}

		////////////////////////////////测试圆和圆求交点///////////////////////////////////

		TEST_METHOD(TestMethod8) //外离
		{
			Circle c1(0, 0, 1);
			Circle c2(5, 4, 2);

			vector<Point> v = c1.get_c_c(c2);
			bool flag = false;

			if (v.size() == 0) flag = true;
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod9) //内切
		{
			Circle c1(0, 0, 2);
			Circle c2(1, 0, 1);

			vector<Point> v = c1.get_c_c(c2);
			bool flag = false;

			if (v.size() == 1) {
				if (v[0].x == 2 && v[0].y == 0) {
					flag = true;
				}
			}
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod10) //外切
		{
			Circle c1(0, 0, 2);
			Circle c2(3, 0, 1);

			vector<Point> v = c1.get_c_c(c2);
			bool flag = false;

			if (v.size() == 1) {
				if (v[0].x == 2 && v[0].y == 0) {
					flag = true;
				}
			}
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod11) //内含
		{
			Circle c1(0, 0, 1);
			Circle c2(5, 4, 20);

			vector<Point> v = c1.get_c_c(c2);
			bool flag = false;

			if (v.size() == 0) flag = true;
			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(TestMethod12) //相交
		{
			Circle c1(0, 0, 5);
			Circle c2(6, 0, 5);

			vector<Point> v = c1.get_c_c(c2);
			bool flag = false;

			if (v.size() == 2) {
				if (v[0].x == 3 && v[0].y == 4 && v[1].x == 3 && v[1].y == -4) {
					flag = true;
				}
				if (v[0].x == 3 && v[0].y == -4 && v[1].x == 3 && v[1].y == 4) {
					flag = true;
				}
			}
			Assert::AreEqual(true, flag);
		}
	};
}

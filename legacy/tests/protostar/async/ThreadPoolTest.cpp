///
/// ThreadPoolTest.cpp
/// tests
///
/// Refer to LICENSE.txt for more details.
///

#include <gtest/gtest.h>
#include <galaxy/async/ThreadPool.hpp>

TEST(ThreadPool, full_test)
{
	std::atomic<int> count = 0;
	pr::ThreadPool<1> pool;
	pr::Task task;
	task.set([&]() {
		count = 2;
	});

	pool.queue(&task);
	pool.start();

	task.wait_until_done();

	pool.end();

	EXPECT_EQ(count.load(), 2);
}
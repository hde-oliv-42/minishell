#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../munit/munit.h"
#include <unistd.h>
#include "../../src/builtins/builtins.h"

#define FINISH { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}

int getcwd_with_nl(char cwd[1024]) {
	int fail = 0;
	int success = 1;
	if (!getcwd(cwd, 1024))
		return (fail);

	char *end = strchr(cwd, '\0');
	end[0] = '\n';
	end[1] = '\0';
	return (success);
}

MunitResult test_default_pwd(const MunitParameter params[], void *user_data_or_fixture)
{
	int out[2];
	char buf[1024];
	char cwd[1024];

	pipe(out);
	dup2(out[1], 1);

	pwd(); // actual test lol

	int size = read(out[0], buf, 1024);
	buf[size] = '\0';
	if (!getcwd_with_nl(cwd))
		return (MUNIT_ERROR);

	munit_assert_string_equal(buf, cwd);

	return (MUNIT_OK);
}

MunitResult test_changing_dir(const MunitParameter params[], void *user_data_or_fixture)
{
	int out[2];
	char printed_dir[1024];

	pipe(out);
	dup2(out[1], 1);
	if (chdir("/"))
		return (MUNIT_ERROR);

	pwd(); // actual test lol

	int size = read(out[0], printed_dir, 1024);
	printed_dir[size] = '\0';

	munit_assert_string_equal(printed_dir, "/\n");

	return (MUNIT_OK);
}

MunitTest tests[] = {
	{ "/test initial cwd", test_default_pwd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
	{ "/test changing directory", test_changing_dir, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
	FINISH
};

static const MunitSuite suite = {
	"/builtins",
	tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *const argv[])
{
	return munit_suite_main(&suite, NULL, argc, argv);
}

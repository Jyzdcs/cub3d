// Global test resources that need setup/cleanup
FILE	*test_file;
char	*test_filename = "temp_test_file.txt";

void	setUp(void)
{
	// Create a fresh test file before each test runs
	test_file = fopen(test_filename, "w+");
	if (test_file)
	{
		fprintf(test_file, "Test data line 1\nTest data line 2\n");
		fseek(test_file, 0, SEEK_SET); // Reset position to start
	}
}

void	tearDown(void)
{
	// Clean up after each test completes
	if (test_file)
	{
		fclose(test_file);
		test_file = NULL;
	}
	remove(test_filename); // Delete the temp file
}

void	test_file_read_line_count(void)
{
	int	count;

	// Test assumes file is already set up
	TEST_ASSERT_NOT_NULL(test_file);
	count = count_lines_in_file(test_filename);
	TEST_ASSERT_EQUAL_INT(2, count);
}

void	test_file_append_content(void)
{
	// Each test gets a fresh file thanks to setUp
	TEST_ASSERT_NOT_NULL(test_file);

	append_to_file(test_filename, "New line");
	int count = count_lines_in_file(test_filename);
	TEST_ASSERT_EQUAL_INT(3, count);
}
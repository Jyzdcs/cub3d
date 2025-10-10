# Pull Request: Map Content Validation Implementation

## Overview

This PR implements a robust map file validation system for Cub3D. The implementation ensures map files follow the required format with proper identifiers, textures, colors, and map layout.

## Implementation Details

### Entry Point (`main.c`)

- Processes command line arguments to get map file path
- Initializes game structure
- Passes control to `file_handler` for content validation

### Validation Flow

#### 1. Extension Validation (`file_check.c`)

- `check_extension`: Ensures the file has a `.cub` extension
- Prevents processing of files with incorrect formats

#### 2. File Content Processing (`file_content_check.c`)

- `file_handler`: Main entry point for content validation
  - Checks file existence
  - Loads file content into memory
  - Validates overall structure
- `export_file`: Reads file content line by line into game structure
- `structure_file_is_valid`: Core validation logic for file content
  - Ensures all required identifiers are present (NO, SO, WE, EA, F, C)
  - Checks for duplicate identifiers
  - Verifies no invalid content before identifiers
- `ft_identifiers_register_check`: Prevents duplicate identifiers

#### 3. Helper Functions (`file_content_utils.c`)

- `ft_isspace`: Whitespace detection (spaces, tabs, etc.)
- `ft_comp`: String comparison with special handling for identifiers
- `ft_is_identifier`: Identifies and categorizes lines as texture or color identifiers
- `ft_is_line_empty`: Detects and skips empty or whitespace-only lines

#### 4. Map Position Validation (`file_content_map_at_the_end.c`)

- `ft_map_is_at_the_end`: Ensures map appears at the end of the file
- `ft_start_index_of_the_map`: Locates the first line of the map
- `ft_end_index_of_the_map`: Determines the last line of the map
- `ft_is_char_accepted_in_map`: Validates map characters (0, 1, N, S, E, W)

## Validation Rules

- Files must have `.cub` extension
- Files must contain exactly 6 identifiers (NO, SO, WE, EA, F, C)
- No duplicate identifiers allowed
- No invalid content before all identifiers are defined
- Map must be positioned at the end of the file
- Map must only contain valid characters
- Empty lines are properly handled and skipped

## Error Handling

- Descriptive error messages for all validation failures
- Memory management to prevent leaks
- Graceful exit on any validation error

## Memory Management

- Careful allocation and cleanup of file content memory
- Fixed potential memory leak in identifier validation
- Proper null termination of string arrays

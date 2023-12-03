// Performs a 2D binary search on a 2D array using a divide & conquer approach.
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class 2d_search {

    public static class Coord {
        public int row;
        public int col;
        Coord(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    public static void main(String[] args) {
        String[] lines = load_from_file();
        String[] rows_and_cols = lines[0].split(" ");
        final int row_count = Integer.parseInt(rows_and_cols[0]);
        final int col_count = Integer.parseInt(rows_and_cols[1]);
        final int target = Integer.parseInt(lines[1]);
        final int[][] matrix = parse_matrix(
                row_count,
                col_count,
                lines,
                2,
                2 + row_count);
        Coord result = find(
                target,
                matrix,
                0,
                0,
                row_count - 1,
                col_count - 1);
        if (result == null)
            System.out.println("NOT FOUND");
        else
            System.out.println(result.row + 1 + " " + (result.col + 1));
    }

    private static Coord find(
            final int target,
            final int[][] matrix,
            final int top_left_row,
            final int top_left_col,
            final int bottom_right_row,
            final int bottom_right_col) {
        // Performs a 2-D binary search using a divide & conquer approach. Returns null
        // if the target is not found.
        if (top_left_row > bottom_right_row || top_left_col > bottom_right_col)
            return null;
        final int mid_row = (bottom_right_row - top_left_row) / 2 + top_left_row;
        final int mid_col = (bottom_right_col - top_left_col) / 2 + top_left_col;
        if (matrix[mid_row][mid_col] == target)
            return new Coord(mid_row, mid_col);
        else if (matrix[mid_row][mid_col] > target) {
            Coord result = find(
                    target,
                    matrix,
                    top_left_row,
                    top_left_col,
                    mid_row - 1,
                    bottom_right_col);
            if (result != null)
                return result;
            return find(
                    target,
                    matrix,
                    mid_row,
                    top_left_col,
                    bottom_right_row,
                    mid_col - 1);
        }
        else {  // if (matrix[mid_row][mid_col] < target)
            Coord result = find(
                    target,
                    matrix,
                    mid_row + 1,
                    top_left_col,
                    bottom_right_row,
                    bottom_right_col);
            if (result != null)
                return result;
            return find(
                    target,
                    matrix,
                    top_left_row,
                    mid_col + 1,
                    mid_row,
                    bottom_right_col);
        }
    }

    private static String[] load_from_file() {
        // Loads the contents of input.txt and splits it into lines. input.txt must be
        // in the same directory as this file.
        Scanner input_file = null;
        try {
            input_file = new Scanner(new File("input.txt"));
        } catch (FileNotFoundException e) {
            try {
                // IntelliJ requires this, but the `javac` and `java` commands require
                // just `"input.txt"`.
                input_file = new Scanner(new File("src/input.txt"));
            } catch (FileNotFoundException e2) {
                System.out.println("File `input.txt` not found.");
                System.exit(1);
            }
        }
        StringBuilder file_content = new StringBuilder();
        while (input_file.hasNextLine()) {
            file_content.append(input_file.nextLine());
            file_content.append("\n");
        }
        String file_content_s = file_content.toString();
        if (file_content_s.contains("\r\n"))
            return file_content_s.split("\r\n");
        return file_content_s.split("\n");
    }

    private static int[][] parse_matrix(
            int rows,
            int cols,
            String[] source_lines,
            int start_line,
            int end_line) {
        // Converts part of the given strings into a matrix of the chosen dimensions.
        // The given dimensions must match that of the numbers in the given strings.
        assert rows == end_line - start_line;
        int line = start_line;
        int[][] matrix = new int[rows][cols];
        for (int row = 0; row < rows; line++, row++) {
            String[] nums = source_lines[line].split("\s");
            assert cols == nums.length;
            for (int col = 0; col < cols; col++)
                matrix[row][col] = Integer.parseInt(nums[col]);
        }
        return matrix;
    }
}

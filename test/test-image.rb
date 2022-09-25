class TestImage < Test::Unit::TestCase
  include Helper::Fixture

  sub_test_case(".read") do
    def test_valid
      image = CV::Image.read(fixture_path("mail-forward.png").to_s,
                             :unchanged)
      assert do
        not image.empty?
      end
    end

    def test_nonexistent
      assert_raise(CV::ImageError::Read) do
        CV::Image.read(fixture_path("nonexistent.png").to_s, :unchanged)
      end
    end
  end

  sub_test_case("instance methods") do
    def setup
      @image = CV::Image.read(fixture_path("mail-forward.png").to_s,
                              :unchanged)
    end

    test("#element_size") do
      assert_equal(4, @image.element_size)
    end

    test("#channel_size") do
      assert_equal(1, @image.channel_size)
    end

    test("#n_channels") do
      assert_equal(4, @image.n_channels)
    end

    test("#n_rows") do
      assert_equal(32, @image.n_rows)
    end

    test("#n_columns") do
      assert_equal(32, @image.n_columns)
    end

    sub_test_case("#write") do
      def test_success
        jpeg = Tempfile.new(["opnecv-glib-write", ".jpeg"])
        @image.write(jpeg.path)
        image = CV::Image.read(jpeg.path, :unchanged)
        assert do
          not image.empty?
        end
      end

      def test_unsupported_format
        unknown = Tempfile.new(["opnecv-glib-write", ".unknown"])
        assert_raise(CV::ImageError::Write) do
          @image.write(unknown.path)
        end
      end
    end

    sub_test_case("#convert_color") do
      def test_flip_flop
        rgba = @image.convert_color(:bgra2rgba)
        assert_not_equal(@image.bytes.to_s,
                         rgba.bytes.to_s)
        bgra = rgba.convert_color(:rgba2bgra)
        assert_equal(@image.bytes.to_s,
                     bgra.bytes.to_s)
      end
    end

    sub_test_case("#arrowed_line") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_arrowed_line(CV::Point.new(10, 0),
                                 CV::Point.new(10, 30),
                                 CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point1 = CV::Point.new(10, 0)
        point2 = CV::Point.new(10, 30)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        drawing_options.tip_length = 1
        cloned_image.draw_arrowed_line(point1, point2, color) # draw without options
        @image.draw_arrowed_line(point1,
                                 point2,
                                 color,
                                 drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#circle") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_circle(CV::Point.new(16, 16),
                           10,
                           CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point = CV::Point.new(16, 16)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        cloned_image.draw_circle(point, 10, color) # draw without options
        @image.draw_circle(point,
                           10,
                           color,
                           drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#marker") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_marker(CV::Point.new(16, 16),
                           CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point = CV::Point.new(16, 16)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.marker_type = :triangle_up
        drawing_options.marker_size = 30
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        cloned_image.draw_marker(point, color) # draw without options
        @image.draw_marker(point,
                           color,
                           drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#ellipse with point") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_ellipse_point(CV::Point.new(16, 16),
                                  CV::Size.new(10, 8),
                                  45,
                                  0,
                                  300,
                                  CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 2
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        @image.draw_ellipse_point(CV::Point.new(16, 16),
                                  CV::Size.new(10, 8),
                                  45,
                                  0,
                                  300,
                                  CV::Color.new(255, 127, 0, 2),
                                  drawing_options)
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#line") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_line(CV::Point.new(10, 10),
                         CV::Point.new(30, 20),
                         CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point1 = CV::Point.new(10, 10)
        point2 = CV::Point.new(30, 20)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        cloned_image.draw_line(point1, point2, color) # draw without options
        @image.draw_line(point1,
                         point2,
                         color,
                         drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#put_text") do
      def test_simple
        cloned_image = @image.clone
        @image.put_text("hello",
                        CV::Point.new(0, 30),
                        :hershey_simplex, 2,
                        CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point = CV::Point.new(0, 16)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.use_bottom_left_origin = true
        cloned_image.put_text("Hello",
                              point,
                              :hershey_simplex,
                              2,
                              color) # draw without options
        @image.put_text("Hello",
                        point,
                        :hershey_simplex,
                        2,
                        color,
                        drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#rectangle") do
      def test_simple
        cloned_image = @image.clone
        @image.draw_rectangle(CV::Rectangle.new(15, 20, 5, 10),
                              CV::Color.new(255, 127, 0, 2))
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        rect = CV::Rectangle.new(15, 20, 5, 10)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        cloned_image.draw_rectangle(rect, color) # draw without options
        @image.draw_rectangle(rect,
                              color,
                              drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    sub_test_case("#rectangle with points") do
      def test_simple
        cloned_image = @image.clone
        color = CV::Color.new(255, 127, 0, 2)
        cloned_image.draw_rectangle(CV::Rectangle.new(5, 10, 11, 11),
                                    color) # draw with rectangle
        @image.draw_rectangle_points(CV::Point.new(5, 10),
                                     CV::Point.new(15, 20),
                                     color) # draw with points
        assert_equal(cloned_image.bytes.to_s,
                     @image.bytes.to_s)
      end

      def test_drawing_options
        cloned_image = @image.clone
        point1 = CV::Point.new(5, 10)
        point2 = CV::Point.new(15, 20)
        color = CV::Color.new(255, 127, 0, 2)
        drawing_options = CV::DrawingOptions.new
        drawing_options.thickness = 5
        drawing_options.line_type = :line_aa
        drawing_options.shift = 2
        cloned_image.draw_rectangle_points(point1,
                                           point2,
                                           color) # draw without options
        @image.draw_rectangle_points(point1,
                                     point2,
                                     color,
                                     drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end

    def test_abs_diff
      lined_image = @image.clone
      lined_image.draw_line(CV::Point.new(10, 10),
                            CV::Point.new(30, 20),
                            CV::Color.new(255, 127, 0, 2))
      expected_path = fixture_path("mail-forward-lined-abs-diff.png")
      expected = CV::Image.read(expected_path.to_s,
                                :unchanged)
      assert_equal(expected.bytes.to_s,
                   @image.abs_diff(lined_image).bytes.to_s)
    end

    def test_split
      spliited_data = @image.bytes.to_s.each_char.group_by.with_index do |_, i|
        i % 4
      end
      splitted_image_data = @image.split.collect do |splitted_image|
        splitted_image.bytes.to_s
      end
      assert_equal([
                     spliited_data[0].join(""),
                     spliited_data[1].join(""),
                     spliited_data[2].join(""),
                     spliited_data[3].join(""),
                   ],
                   splitted_image_data)
    end

    def test_median_blur
      blur_image = @image.median_blur(7)
      assert_not_equal(@image.bytes.to_s,
                       blur_image.bytes.to_s)
    end

    data(:ksize, [-1, 0, 2])
    def test_median_blur_invalid_argument(data)
      ksize = data[:ksize]
      message = "ksize must be odd and greater than 1: <#{ksize}>"
      assert_raise(CV::ImageError::Filter.new(message)) do
        @image.median_blur(ksize)
      end

    end
    def test_image_filter_options
      options = CV::ImageFilterOptions.new
      options.delta
      options.scale
      options.iterations
      options.max_level
#      options.sigma_y
      options.border_type
      options.ktype
      options.normalize?
    end

    def test_blur
      size = CV::Size.new(10, 8)
      blur_image = @image.blur(size)
      blur_image = @image.blur(size,CV::ImageFilterOptions.new)
      assert_not_equal(@image.bytes.to_s,
                       blur_image.bytes.to_s)
    end

=begin
    def test_get_deriv_kernels
      dx = 2
      dy = 2
      ksize = 3
      filtered_image = @image.get_deriv_kernels(dx,dy,ksize)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)

      options = CV::ImageFilterOptions.new
      options.ktype = 6
      options.normalize = true
      filtered_image = @image.get_deriv_kernels(dx,dy,ksize,options)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)
    end
=end

    def test_laplacian
      ddepth = 5
      filtered_image = @image.laplacian(ddepth)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)

      options = CV::ImageFilterOptions.new
      options.ksize = 1
#      options.ksize = 0
      filtered_image = @image.laplacian(ddepth,options)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)
    end

    def test_filter2d
      ddepth = -1
      filtered_image = @image.filter2d(ddepth,@image)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)

      options = CV::ImageFilterOptions.new
      options.ksize = 1
#      options.ksize = 0
      filtered_image = @image.filter2d(ddepth,@image,options)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)
    end

    def test_sobel
      ddepth = 5
      filtered_image = @image.sobel(ddepth,1,1)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)

      options = CV::ImageFilterOptions.new
      #
      options.ksize = 3
      filtered_image = @image.sobel(ddepth,1,1,options)
      assert_not_equal(@image.bytes.to_s,
                       filtered_image.bytes.to_s)

    end
  end
end

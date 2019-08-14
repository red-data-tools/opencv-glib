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
        drawing_options.line_type = CV::LineType::LINE_AA
        drawing_options.shift = 2
        cloned_image.draw_rectangle(rect, color) # draw without options
        @image.draw_rectangle(rect,
                              color,
                              drawing_options) # draw with options
        assert_not_equal(cloned_image.bytes.to_s,
                         @image.bytes.to_s)
      end
    end
  end
end

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
  end
end

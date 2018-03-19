class TestImage < Test::Unit::TestCase
  include Helper::Fixture

  sub_test_case(".read") do
    def test_valid
      image = CV::Image.read(fixture_path("mail-forward.png").to_s)
      assert do
        not image.empty?
      end
    end

    def test_nonexistent
      assert_raise(CV::Error::ImageRead) do
        CV::Image.read(fixture_path("nonexistent.png").to_s)
      end
    end
  end
end

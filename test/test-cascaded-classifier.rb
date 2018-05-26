class TestMatrix < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_name
      assert_nothing_raised do
        CV::CascadeClassifier.new("frontalface_default")
      end
    end

    def test_basename
      assert_nothing_raised do
        CV::CascadeClassifier.new("haarcascade_frontalface_default.xml")
      end
    end

    def test_relative_path
      assert_nothing_raised do
        CV::CascadeClassifier.new("haarcascades/haarcascade_frontalface_default.xml")
      end
    end
  end
end

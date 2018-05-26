class TestColor < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_brightness
      color = CV::Color.new(0.9)
      assert_equal(0.9, color.brightness)
    end

    def test_color
      color = CV::Color.new(1, 2, 3)
      assert_equal([1, 2, 3],
                   [
                     color.pixel0,
                     color.pixel1,
                     color.pixel2,
                   ])
    end

    def test_color_alpha
      color = CV::Color.new(1, 2, 3, 4)
      assert_equal([1, 2, 3, 4],
                   [
                     color.pixel0,
                     color.pixel1,
                     color.pixel2,
                     color.alpha,
                   ])
    end
  end
end

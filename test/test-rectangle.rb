class TestRectangle < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_empty
      rectangle = CV::Rectangle.new
      assert_equal([0, 0, 0, 0],
                   [
                     rectangle.x,
                     rectangle.y,
                     rectangle.width,
                     rectangle.height,
                   ])
    end

    def test_corner_and_size
      rectangle = CV::Rectangle.new(1, 2, 3, 4)
      assert_equal([1, 2, 3, 4],
                   [
                     rectangle.x,
                     rectangle.y,
                     rectangle.width,
                     rectangle.height,
                   ])
    end
  end
end

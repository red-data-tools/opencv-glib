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

  sub_test_case("#clip_line") do
    def test_true
      rectangle = CV::Rectangle.new(10, 10, 80, 80)
      pt1 = CV::Point.new(0, 10)
      pt2 = CV::Point.new(100, 90)
      ret, new_pt1, new_pt2 = rectangle.clip_line(pt1, pt2)
      assert_equal([true, 10, 17, 89, 81],
                   [
                     ret,
                     new_pt1.x,
                     new_pt1.y,
                     new_pt2.x,
                     new_pt2.y
                   ])
    end

    def test_false
      rectangle = CV::Rectangle.new(10, 10, 80, 80)
      pt1 = CV::Point.new(200, 200)
      pt2 = CV::Point.new(300, 300)
      ret, new_pt1, new_pt2 = rectangle.clip_line(pt1, pt2)
      assert_equal([false, 200, 200, 300, 300],
                   [
                     ret,
                     new_pt1.x,
                     new_pt1.y,
                     new_pt2.x,
                     new_pt2.y
                   ])
    end
  end
end

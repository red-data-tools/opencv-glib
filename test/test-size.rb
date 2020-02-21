class TestSize < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_empty
      size = CV::Size.new
      assert_equal([0, 0],
                   [
                     size.width,
                     size.height,
                   ])
    end

    def test_width_and_height
      size = CV::Size.new(10, 20)
      assert_equal([10, 20],
                   [
                     size.width,
                     size.height,
                   ])
    end
  end

  sub_test_case("#clip_line") do
    def test_true
      size = CV::Size.new(100, 100)
      pt1 = CV::Point.new(-10, 0)
      pt2 = CV::Point.new(110, 100)
      inside, new_pt1, new_pt2 = size.clip_line(pt1, pt2)
      assert_equal([true, 0, 8, 99, 91],
                   [
                     inside,
                     new_pt1.x,
                     new_pt1.y,
                     new_pt2.x,
                     new_pt2.y
                    ])
    end

    def test_false
      size = CV::Size.new(100, 100)
      pt1 = CV::Point.new(200, 200)
      pt2 = CV::Point.new(300, 300)
      inside, new_pt1, new_pt2 = size.clip_line(pt1, pt2)
      assert_equal([false, 200, 200, 300, 300],
                   [
                     inside,
                     new_pt1.x,
                     new_pt1.y,
                     new_pt2.x,
                     new_pt2.y
                    ])
    end
  end
end

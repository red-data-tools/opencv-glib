class TestPoint < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_empty
      point = CV::Point.new
      assert_equal([0, 0],
                   [
                     point.x,
                     point.y,
                   ])
    end

    def test_x_and_y
      point = CV::Point.new(1, 2)
      assert_equal([1, 2],
                   [
                     point.x,
                     point.y,
                   ])
    end
  end
end

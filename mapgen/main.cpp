#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/polygon/voronoi.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
namespace cairo{
#include <cairo.h>
}

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
namespace gil = boost::gil;
namespace bp = boost::polygon;


struct Point{
  double x;
  double y;
  double z;
  Point (double x, double y, double z) : x(x), y(y), z(z) {}
};

template <>
struct bp::geometry_concept<Point> { typedef point_concept type; };
   
template <>
struct bp::point_traits<Point> {
  typedef int coordinate_type;
    
  static inline coordinate_type get(const Point& point, orientation_2d orient) {
    return (orient == HORIZONTAL) ? point.x : point.y;
  }
};


int main() {
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, 10000);
    std::vector< Point> points;
    for(int i = 0; i < 1000; ++i) {
        double x, y, z;
        x = index_dist(rng) / 10.0;
        y = index_dist(rng) / 10.0;
        z = index_dist(rng);
        Point b {x, y, z};
        points.push_back(b);
    }
    cairo::cairo_surface_t *surface;
    cairo::cairo_t *cr;

    surface = cairo::cairo_image_surface_create (cairo::CAIRO_FORMAT_ARGB32, 1000, 1000);
    cr = cairo::cairo_create (surface);
    cairo::cairo_set_line_width (cr, 1.0);
    cairo::cairo_set_source_rgb (cr, 0, 0, 255);
    bp::voronoi_diagram<double> vd;
    construct_voronoi(points.begin(), points.end(), &vd);
    BOOST_FOREACH(Point const &b, points){
      double x = b.x;
      double y = b.y;
      //view(static_cast <int> (std::floor(x)), static_cast <int> (std::floor(y))) = red;
    }
    for (bp::voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
        it != vd.edges().end(); ++it) {
      if (it->vertex1() != NULL && it->vertex0() != NULL && it->is_primary()) {
        Point p1 {it->vertex1()->x(), it->vertex1()->y(), 0.0};
        Point p2 {it->vertex0()->x(), it->vertex0()->y(), 0.0};
        cairo::cairo_move_to (cr, static_cast<int>(std::floor(p1.x)), static_cast <int> (std::floor(p1.y)));
        cairo::cairo_line_to (cr, static_cast<int>(std::floor(p2.x)), static_cast <int> (std::floor(p2.y)));
        cairo::cairo_stroke(cr);
      }
   }
  cairo::cairo_save(cr);
  cairo::cairo_surface_write_to_png(surface, "test1.png");
  for(int i = 0; i < 4; i++){
    cairo::cairo_set_source_rgb (cr, 1.0, 1.0, 1.0); 
    cairo::cairo_paint (cr);
    cairo::cairo_set_source_rgb (cr, 0, 0, 255);
    bp::voronoi_diagram<double> vd2;
    bp::construct_voronoi(points.begin(), points.end(), &vd2);
    for (bp::voronoi_diagram<double>::const_cell_iterator it = vd2.cells().begin();
         it != vd2.cells().end(); ++it) {
      const bp::voronoi_diagram<double>::cell_type &cell = *it;
      const bp::voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
      Point avarage {0.0, 0.0, 0.0};
      int count = 0;
      do {
        if (edge->is_primary() && edge->vertex1() != NULL && edge->vertex0() != NULL){
          avarage.x += edge->vertex0()->x();
          avarage.y += edge->vertex0()->y();
          avarage.x += edge->vertex1()->x();
          avarage.y += edge->vertex1()->y();
          count += 2;
        }
        edge = edge->next();
      } while (edge != cell.incident_edge());
      avarage.x /= count;
      avarage.y /= count;
      if (it->contains_point()) {
        std::size_t index = it->source_index();
        points[index].x = avarage.x;
        points[index].y = avarage.y;
      }
    }
    for (bp::voronoi_diagram<double>::const_cell_iterator it = vd2.cells().begin();
         it != vd2.cells().end(); ++it) {
      const bp::voronoi_diagram<double>::cell_type &cell = *it;
      const bp::voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
      bool first = true;
      std::size_t index = it->source_index();
      int grsc = (points[index].z / 10000.0) * 255.0;
      cairo::cairo_set_source_rgb (cr, grsc, grsc, 255);
      std::cout << grsc << std::endl;
      do {
        if (edge->is_primary() && edge->vertex1() != NULL && edge->vertex0() != NULL){
          if(first){
            first = false;
            Point p1 {edge->vertex0()->x(), edge->vertex0()->y(), 0.0};
            cairo::cairo_move_to (cr, static_cast<int>(std::floor(p1.x)), static_cast <int> (std::floor(p1.y)));
          } 
          Point p2 {edge->vertex1()->x(), edge->vertex1()->y(), 0.0};
          cairo::cairo_line_to (cr, static_cast<int>(std::floor(p2.x)), static_cast <int> (std::floor(p2.y)));
        }
        edge = edge->next();
      } while (edge != cell.incident_edge());
      cairo::cairo_close_path(cr);
      cairo::cairo_fill(cr);
    }
    cairo::cairo_set_source_rgb (cr, 255, 0, 0);
    for (bp::voronoi_diagram<double>::const_edge_iterator it = vd2.edges().begin();
        it != vd2.edges().end(); ++it) {
      if (it->vertex1() != NULL && it->vertex0() != NULL && it->is_primary()) {
        Point p1 {it->vertex1()->x(), it->vertex1()->y(), 0.0};
        Point p2 {it->vertex0()->x(), it->vertex0()->y(), 0.0};
        cairo::cairo_move_to (cr, static_cast<int>(std::floor(p1.x)), static_cast <int> (std::floor(p1.y)));
        cairo::cairo_line_to (cr, static_cast<int>(std::floor(p2.x)), static_cast <int> (std::floor(p2.y)));
        cairo::cairo_stroke(cr);
      }
    }
      for (bp::voronoi_diagram<double>::const_edge_iterator it = vd2.edges().begin();
          it != vd2.edges().end(); ++it) {
        if (it->vertex1() != NULL && it->vertex0() != NULL && it->is_primary()) {
          Point p1 {it->vertex1()->x(), it->vertex1()->y(), 0.0};
          Point p2 {it->vertex0()->x(), it->vertex0()->y(), 0.0};
          cairo::cairo_move_to (cr, static_cast<int>(std::floor(p1.x)), static_cast <int> (std::floor(p1.y)));
          cairo::cairo_line_to (cr, static_cast<int>(std::floor(p2.x)), static_cast <int> (std::floor(p2.y)));
          cairo::cairo_stroke(cr);
        }
     }
    cairo::cairo_save(cr);
    cairo::cairo_surface_write_to_png(surface, std::string("test" + std::to_string( i + 2 )+  ".png").c_str());
  }
}


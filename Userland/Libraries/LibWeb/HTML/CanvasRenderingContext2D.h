/*
 * Copyright (c) 2020-2022, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021-2022, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefCountForwarder.h>
#include <AK/Variant.h>
#include <LibGfx/AffineTransform.h>
#include <LibGfx/Color.h>
#include <LibGfx/Forward.h>
#include <LibGfx/Painter.h>
#include <LibGfx/Path.h>
#include <LibWeb/Bindings/Wrappable.h>
#include <LibWeb/DOM/ExceptionOr.h>
#include <LibWeb/HTML/Canvas/CanvasDrawImage.h>
#include <LibWeb/HTML/Canvas/CanvasDrawPath.h>
#include <LibWeb/HTML/Canvas/CanvasFillStrokeStyles.h>
#include <LibWeb/HTML/Canvas/CanvasImageData.h>
#include <LibWeb/HTML/Canvas/CanvasPath.h>
#include <LibWeb/HTML/Canvas/CanvasPathDrawingStyles.h>
#include <LibWeb/HTML/Canvas/CanvasRect.h>
#include <LibWeb/HTML/Canvas/CanvasState.h>
#include <LibWeb/HTML/Canvas/CanvasText.h>
#include <LibWeb/HTML/Canvas/CanvasTransform.h>
#include <LibWeb/HTML/CanvasGradient.h>
#include <LibWeb/Layout/InlineNode.h>
#include <LibWeb/Layout/LineBox.h>

namespace Web::HTML {

// https://html.spec.whatwg.org/multipage/canvas.html#canvasimagesource
// NOTE: This is the Variant created by the IDL wrapper generator, and needs to be updated accordingly.
using CanvasImageSource = Variant<NonnullRefPtr<HTMLImageElement>, NonnullRefPtr<HTMLCanvasElement>>;

class CanvasRenderingContext2D
    : public RefCountForwarder<HTMLCanvasElement>
    , public Bindings::Wrappable
    , public CanvasPath
    , public CanvasState
    , public CanvasTransform<CanvasRenderingContext2D>
    , public CanvasFillStrokeStyles<CanvasRenderingContext2D>
    , public CanvasRect
    , public CanvasDrawPath
    , public CanvasText
    , public CanvasDrawImage
    , public CanvasImageData
    , public CanvasPathDrawingStyles<CanvasRenderingContext2D> {

    AK_MAKE_NONCOPYABLE(CanvasRenderingContext2D);
    AK_MAKE_NONMOVABLE(CanvasRenderingContext2D);

public:
    using WrapperType = Bindings::CanvasRenderingContext2DWrapper;

    static NonnullRefPtr<CanvasRenderingContext2D> create(HTMLCanvasElement& element) { return adopt_ref(*new CanvasRenderingContext2D(element)); }
    ~CanvasRenderingContext2D();

    virtual void fill_rect(float x, float y, float width, float height) override;
    virtual void stroke_rect(float x, float y, float width, float height) override;
    virtual void clear_rect(float x, float y, float width, float height) override;

    virtual DOM::ExceptionOr<void> draw_image_internal(CanvasImageSource const&, float source_x, float source_y, float source_width, float source_height, float destination_x, float destination_y, float destination_width, float destination_height) override;

    virtual void begin_path() override;
    virtual void stroke() override;
    virtual void stroke(Path2D const& path) override;

    virtual void fill_text(String const&, float x, float y, Optional<double> max_width) override;
    virtual void stroke_text(String const&, float x, float y, Optional<double> max_width) override;

    virtual void fill(String const& fill_rule) override;
    virtual void fill(Path2D& path, String const& fill_rule) override;

    virtual RefPtr<ImageData> create_image_data(int width, int height) const override;
    virtual DOM::ExceptionOr<RefPtr<ImageData>> get_image_data(int x, int y, int width, int height) const override;
    virtual void put_image_data(ImageData const&, float x, float y) override;

    virtual void reset_to_default_state() override;

    NonnullRefPtr<HTMLCanvasElement> canvas_for_binding() const;

    virtual RefPtr<TextMetrics> measure_text(String const& text) override;

    virtual void clip() override;

private:
    explicit CanvasRenderingContext2D(HTMLCanvasElement&);

    struct PreparedTextGlyph {
        unsigned int c;
        Gfx::IntPoint position;
    };

    struct PreparedText {
        Vector<PreparedTextGlyph> glyphs;
        Gfx::TextAlignment physical_alignment;
        Gfx::IntRect bounding_box;
    };

    void did_draw(Gfx::FloatRect const&);
    PreparedText prepare_text(String const& text, float max_width = INFINITY);

    OwnPtr<Gfx::Painter> painter();

    HTMLCanvasElement& canvas_element();
    HTMLCanvasElement const& canvas_element() const;

    void stroke_internal(Gfx::Path const&);
    void fill_internal(Gfx::Path&, String const& fill_rule);

    // https://html.spec.whatwg.org/multipage/canvas.html#concept-canvas-origin-clean
    bool m_origin_clean { true };
};

enum class CanvasImageSourceUsability {
    Bad,
    Good,
};

DOM::ExceptionOr<CanvasImageSourceUsability> check_usability_of_image(CanvasImageSource const&);
bool image_is_not_origin_clean(CanvasImageSource const&);

}

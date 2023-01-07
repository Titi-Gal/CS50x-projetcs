$(".book-button").on("click", function() {
    if ($(this).hasClass("btn-outline-success")) {
        $(this).removeClass("btn-outline-success");
        $(this).addClass("btn-outline-danger");
        $(this).attr("value", "Unbook");
        $(this).prev().prop("disabled", true);
    }
    else if ($(this).hasClass("btn-outline-danger")) {
        $(this).removeClass("btn-outline-danger");
        $(this).addClass("btn-outline-success");
        $(this).attr("value", "Book");
        $(this).prev().prop("disabled", false);
    }
});

$(".button-week").on("click", function() {
    $(".times-dropdown").removeClass("show");
});

$('.profile-button').on("click", function() {
    if ($(this).attr("value") === "Edit") {
        $(this).removeClass("btn-danger");
        $(this).addClass("btn-success");
        $(this).attr("value", "Confirm");
        $('.profile-form').prop("disabled", false)
    }
    else if ($(this).attr("value") === "Confirm") {
        $(this).attr("value", "Edit")
        $(this).removeClass("btn-success");
        $(this).addClass("btn-danger");
        $('.profile-form').prop("disabled", true)
    }
});